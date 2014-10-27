var hideIgnores = {
    userMenu : false
};

//Login show/hide
var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    if(visible){ $('#username').focus(); }
    loginVisible = visible;
}

//UserMenu show/hide
var userMenuVisible = false;
function setUserMenuVisible(visible){
    if(visible){
        hideIgnores.userMenu = true;
        $('.second-navigation').removeClass('hidden');
        $('#nav-user').addClass('active');
    } else {
        $('.second-navigation').addClass('hidden');
        $('#nav-user').removeClass('active');
    }
    userMenuVisible = visible;
}

//Hide optional content
function hideAll() {
    if(!hideIgnores.userMenu){ setUserMenuVisible(false); }
    hideIgnores.userMenu = false;
}

$(document).ready(function() {
    //Register hide all listener
    $('html').click(function() { hideAll(); });
    //Open connection
    api.connect(function(){
        //On connection open, continue session if exists
        if(api.getSid() != null){
            api.send(ApiRequest.ContinueSession, { sid: api.getSid() });
        }
        //Get conversations
        api.send(ApiRequest.GetConversations);
    });
    //Continue Session (Handle Server Response)
    api.register(ApiRequest.ContinueSession, function(data){
        if(data.s){
            setLoginVisible(false);
            $('#nav-user').text(data.username).append('&#x25BE;');
            $('#nav-user').removeClass('hidden');
            $('#toggle-login').addClass('hidden');
        }
    });
    //Login
    $('#toggle-login').click(function(){ setLoginVisible(!loginVisible); });
    $('#cancel-login').click(function(){ setLoginVisible(false); });
    $('#login-form').submit(function(){
        api.send(ApiRequest.Login, {username : $('#username').val(), password : $('#password').val()});
        return false;
    });
    api.register(ApiRequest.Login, function(data){
        if(!data.s){ alert('Login failed: ' + data.error + ' ' + data.error_text); }
        else {
            setLoginVisible(false);
            $('#nav-user').text($('#username').val()).append('&#x25BE;');
            $('#nav-user').removeClass('hidden');
            $('#toggle-login').addClass('hidden');
        }
    });
    //User Menu
    $('#nav-user').click(function(){ setUserMenuVisible(!userMenuVisible); });
    $('#user-menu').click(function(){ setUserMenuVisible(true); }); //Keep open => ignores html click
    //Logout
    $('#logout').click(function(){
        api.send(ApiRequest.Logout);
        api.deleteSid();
        setUserMenuVisible(false);
        setTimeout(function(){ location.reload(); }, 300); //Reload if no answer after 300ms
    });
    api.register(ApiRequest.Logout, function(data){
        location.reload();
    });
    //Conversations
    api.register(ApiRequest.GetConversations, function(data){
        if(data.s){ var key; for(key in data.conversations){ alert(data.conversations[key].title); } }
    });
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
