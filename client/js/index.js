var openRoom = 0;
var user = {
    name : null
};
var hideIgnores = {
    userMenu : false
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
    var key; for(key in msgs){
        var msg = msgs[key];
        if(msg.c in rooms){
            rooms[msg.c].msgs.push(msg);
        }
        if(msg.c == openRoom){
            var message = $('<div />', { id: 'message-' + msg.id, class: 'message' });
            message.append('<span />').addClass('person').text(msg.user);
            message.append('<span />').addClass('time').text(msg.time);
            message.append('<span />').addClass('message-content').text(msg.message);
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
        return false; //Prevent native submit
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
    //Public Conversations
    api.register(ApiRequest.GetConversations, function(data){
        if(data.s){
            var first = true;
            var key; for(key in data.conversations){
                var room = data.conversations[key];
                //Open first conversation right away (Has to be done by separate request for now)
                if(first) { first = false; //once
                    api.send(ApiRequest.OpenConversation, { id: room.id });
                }
                //Show room
                $('#rooms').append('<a class="room" id="room-' + room.id + '"></a>');
                $('#room-' + room.id).text(room.title);
                //Open Public Conversation
                $('#room-' + room.id).click(function(inner){ return function(){
                    api.send(ApiRequest.OpenConversation, { id: inner.id });
                }}(room));
                //Add to internal data
                room.msgs = [];
                rooms[room.id] = room;
            }
        }
    });
    //Open Public Conversation (callback)
    api.register(ApiRequest.OpenConversation, function(data){
        if(data.s){
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
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
