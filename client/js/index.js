var openRoom = 0;
var user = {
    id : 0,
    name : null
};
var hideIgnores = {
    userMenu : false,
    registerModal : false
};
var rooms = [
];

//Login show/hide
var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    if(visible){ $('#username').focus(); }
    loginVisible = visible;
}

//Register Modal
var registerVisible = false;
function setRegisterVisible(visible){
    setGreyScreenVisible(visible);
    $('#register-box').stop();
    if(visible){
        $('#register-box').removeClass('hidden');
        $('#register-box').animate({ top: '110px' }, 400, function(){
            $('#register-username').focus();
        });
    } else {
        $('#register-box').animate({ top: '-250px' }, 400, function(){
            $('#register-box').addClass('hidden');
        });
    }
    registerVisible = visible;
}

var greyScreenVisible = false;
function setGreyScreenVisible(visible){
    $('#grey-screen').stop();
    if(visible){
        hideIgnores.registerModal = true;
        if(!greyScreenVisible){ $('#grey-screen').css('opacity', 0); }
        $('#grey-screen').removeClass('hidden');
        $('#grey-screen').animate({ opacity: 0.6 }, 400);
    } else {
        $('#grey-screen').animate({ opacity: 0.0 }, 400, function(){
            $('#grey-screen').addClass('hidden');
        });
    }
    greyScreenVisible = visible;
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

//Display new messages
function receiveMessages(msgs){
    msgs.reverse(); //Order messages correct for view
    var key; for(key in msgs){
        var msg = msgs[key];
        if(msg.c in rooms){
            rooms[msg.c].msgs.push(msg);
        }
        if(msg.c == openRoom){
            var message = $('<div />', { id: 'message-' + msg.id, class: 'message' });
            message.append($('<span />').addClass('person').text(msg.username));
            message.append($('<span />').addClass('time').text(api.formatTime(msg.time)));
            message.append($('<span />').addClass('message-content').text(msg.msg));
            message.addClass(user.id == msg.userid ? 'own' : 'their');
            $('#chat').append(message);
            //Scroll to bottom
            //TODO: disable, if user scrolled manually
            $('#chat').animate({ scrollTop: $('#chat').prop("scrollHeight") }, 1000);
        }
    }
}

//Hide optional content
function hideAll() {
    if(!hideIgnores.userMenu){ setUserMenuVisible(false); }
    hideIgnores.userMenu = false;
    if(!hideIgnores.registerModal){ setRegisterVisible(false); }
    hideIgnores.registerModal = false;
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
            user.id = data.userid;
            user.name = data.username;
            setLoginVisible(false);
            $('#nav-user').text(data.username).append('&#x25BE;');
            $('#nav-user').removeClass('hidden');
            $('#toggle-login').addClass('hidden');

            //Try to Open Last Conversation
            var indexOfDash = window.location.hash.lastIndexOf('-');
            if(indexOfDash > 0){ openRoom = parseInt(window.location.hash.substring(indexOfDash+1)); }
            if(openRoom == NaN || !openRoom || openRoom < 0){ openRoom = 0; }
            if(openRoom > 0){
                rooms[openRoom] = { msgs : [] };
                api.send(ApiRequest.OpenConversation, { c: openRoom });
            }
        }
    });
    //Login
    $('#toggle-login').click(function(){ setLoginVisible(!loginVisible); });
    $('#cancel-login').click(function(){ setLoginVisible(false); });
    $('#login-form').submit(function(){
        api.send(ApiRequest.Login, {username : $('#username').val(), password : $('#password').val()});
        return false; //Prevent native submit
    });
    api.register(ApiRequest.Login, function(data){
        if(!data.s){ alert('Login failed: ' + data.error + ' ' + data.error_text); }
        else {
            user.id = data.userid;
            user.name = data.username;
            setLoginVisible(false);
            $('#nav-user').text(data.username).append('&#x25BE;');
            $('#nav-user').removeClass('hidden');
            $('#toggle-login').addClass('hidden');
            //Reopen conversation, so owned messages are shown correctly
            if(openRoom > 0){ api.send(ApiRequest.OpenConversation, { c: openRoom }); }
        }
    });
    //User Menu
    $('#nav-user').click(function(){ setUserMenuVisible(!userMenuVisible); });
    $('#user-menu').click(function(){ setUserMenuVisible(true); }); //Keep open => ignores html click
    //Logout
    $('#logout').click(function(){
        user.id = 0;
        user.name = null;
        api.send(ApiRequest.Logout);
        api.deleteSid();
        setUserMenuVisible(false);
        setTimeout(function(){ location.reload(); }, 300); //Reload if no answer after 300ms
    });
    api.register(ApiRequest.Logout, function(data){
        location.reload();
    });
    //Public Conversations
    api.register(ApiRequest.GetConversations, function(data){
        if(data.s){
            var openConv = (openRoom == 0);
            var key; for(key in data.conversations){
                var room = data.conversations[key];
                //Show room
                $('#rooms').append('<a class="room" id="room-' + room.id + '" href="#' + room.title + '-' + room.id + '"></a>');
                $('#room-' + room.id).text(room.title);
                //Open Public Conversation
                $('#room-' + room.id).click(function(inner){ return function(){
                    api.send(ApiRequest.OpenConversation, { c: inner.id });
                }}(room));
                //Add to internal data
                room.msgs = [];
                rooms[room.id] = room;
                //Open first conversation right away (Has to be done by separate request for now)
                if(openConv) { openConv = false; //once
                    api.send(ApiRequest.OpenConversation, { c: room.id });
                }
            }
        }
    });
    //Open Public Conversation (callback)
    api.register(ApiRequest.OpenConversation, function(data){
        if(data.s && data.c in rooms){
            $('#chat').empty();
            //Clear msgs to prevent duplicates (for now; Later offline switching may be implemented)
            rooms[data.c].msgs = [];
            openRoom = data.c;
            receiveMessages(data.msgs);
        }
    });
    //Message sending
    $('#sender-form').submit(function(){
        if(openRoom > 0){
            api.send(ApiRequest.SendMessage, { msg: $('#new-message').val(), c: openRoom });
            $('#new-message').val('');
        } else { alert('You must have an open chat room to send messages'); }
        return false; //Prevent native submit
    });
    //Receive message notifications
    api.register(ApiRequest.SendMessage, function(data){
        if(data.s){ receiveMessages(data.msgs); }
    });
    //Register
    $('#register').click(function(){
        setLoginVisible(false);
        setRegisterVisible(true);
    });
    $('#register-modal').click(function(){ hideIgnores.registerModal = true; });
    $('#register-modal-close').click(function(){ setRegisterVisible(false); });
    $('#register-cancel').click(function(){ setRegisterVisible(false); });
    $('#register-form').submit(function(){
        //Check validity
        var userLength = $('#register-username').val().length;
        if(userLength < 2){
            alert('The username is too short');
            $('#register-username').focus();
        } else if(userLength > 24){
            alert('The username is too long');
            $('#register-username').focus();
        } else if($('#register-mail').val().length <= 0){
            alert('A mail address is required');
            $('#register-mail').focus();
        } else if($('#register-password').val().length < 6){
            alert('Password has to be longer than 6 characters');
            $('#register-password').focus();
        } else if($('#register-password').val() != $('#register-password-repeat').val()){
            alert('Passwords have to be the same');
            $('#register-password').focus();
        } else {
            //Valid: Register
            api.send(ApiRequest.Register, {
                username: $('#register-username').val(),
                email: $('#register-mail').val(),
                password: $('#register-password').val()
            });
        }
        return false; //Prevent native submit
    });
    //Register (callback)
    api.register(ApiRequest.Register, function(data){
        if(data.s){
            setRegisterVisible(false);
            setLoginVisible(true);
        } else {
            alert(data.error_text);
        }
    });
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
