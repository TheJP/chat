//Current main room
var openRoom = 0;
//User data
var user = {
    id : 0,
    name : null
};
var hideIgnores = {
    userMenu : false,
    greyScreen : false,
    registerModal : false,
    chpwModal : false,
    profileModal : false,
    profileTip : false
};
//Rooms and cached messages
var rooms = [
];
//Define if a notify blinker is running
var notify = false;
var notifyInterval;
var notifyState = false;

//Login show/hide
var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    if(visible){ $('#username').focus(); }
    loginVisible = visible;
}

//Generic Modal Code
function setModalVisible(modal, focus, visible){
    setGreyScreenVisible(visible);
    modal.stop();
    if(visible){
        modal.removeClass('hidden');
        modal.animate({ top: '110px' }, 400, function(){
            focus.focus();
        });
    } else {
        modal.animate({ top: '-250px' }, 400, function(){
            modal.addClass('hidden');
        });
    }
}

//Register Modal
var registerVisible = false;
function setRegisterVisible(visible){
    setModalVisible($('#register-box'), $('#register-username'), visible);
    if(visible){  hideIgnores.registerModal = true; }
    registerVisible = visible;
}

//Change Password Modal
var chpwVisible = false;
function setChpwVisible(visible){
    setModalVisible($('#chpw-box'), $('#chpw-old-password'), visible);
    if(visible){  hideIgnores.chpwModal = true; }
    chpwVisible = visible;
}

//Error Modal
var errorVisible = false;
function setErrorVisible(visible){
    setModalVisible($('#error-box'), $('#error-modal'), visible);
    if(visible){ $('#error-modal-load').addClass('hidden'); }
    errorVisible = visible;
    hideAll();
}

//Change Profile Modal
var profileVisible = false;
function setProfileVisible(visible){
    //Only allow editing, current profile was loaded
    $('#profile-status').prop('disabled', true);
    $('#profile-description').prop('disabled', true);
    //Show / Hide Modal
    setModalVisible($('#profile-box'), $('#profile-status'), visible);
    if(visible){  hideIgnores.profileModal = true; }
    profileVisible = visible;
}

//Grey screen (used for modals)
var greyScreenVisible = false;
function setGreyScreenVisible(visible){
    if(hideIgnores.greyScreen){ return; }
    $('#grey-screen').stop();
    if(visible){
        hideIgnores.greyScreen = true;
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

//Profile ToolTip
var profileTipVisible = false;
function setProfileTipVisible(visible){
    $('#profile-tooltip').stop();
    if(visible){
        $('#profile-tooltip').fadeIn(400);
    } else {
        $('#profile-tooltip').fadeOut(400);
    }
    profileTipVisible = visible;
}

//Display new messages
function receiveMessages(msgs, showNotification){
    if(!showNotification){ showNotification = false; } //Default value
    var newmsg = false;
    msgs.reverse(); //Order messages correct for view
    var key; for(key in msgs){
        var msg = msgs[key];
        if(msg.c in rooms){
            rooms[msg.c].msgs.push(msg);
        }
        if(msg.c == openRoom){
            newmsg = true;
            var message = $('<div />', { id: 'message-' + msg.id, class: 'message' });
            message.append($('<a />',
                { id: 'person-' + msg.id, class: 'person', href: '#'}).text(msg.username));
            message.append($('<span />').addClass('time').text(api.formatTime(msg.time)));
            message.append($('<span />').addClass('message-content').text(msg.msg));
            message.addClass(user.id == msg.userid ? 'own' : 'their');
            $('#chat').append(message);
            $('#person-' + msg.id).click(function(id){ return function(){
                setProfileTipVisible(false);
                var pos = this.getBoundingClientRect();
                $('#profile-tooltip').css({ top: pos.bottom, left: pos.left });
                api.send(ApiRequest.GetUser, { userid: id });
            } }(msg.userid));
            //Scroll to bottom
            $("#chat").scrollTop($("#chat")[0].scrollHeight);
        } else {
            //Show notification
            if(msg.c in rooms){
                ++rooms[msg.c].counter;
                $('#room-counter-' + msg.c).text('[' + rooms[msg.c].counter + '] ');
            }
        }
    }
    //Notify if in other tab
    if(showNotification && document.hidden && newmsg && !notify){
        notifyInterval = setInterval(function(){
            document.title = notifyState ? 'Chat' : '[+] Chat';
            notifyState = !notifyState;
        }, 400);
        notify = true;
    }
}

//Register Valid
function registerValid(){
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
        return true;
    }
    return false;
}

//Change Password Valid
function chpwValid(){
    if($('#chpw-password').val().length < 6){
        alert('Password has to be longer than 6 characters');
        $('#chpw-password').focus();
    } else if($('#chpw-password').val() != $('#chpw-password-repeat').val()){
        alert('Passwords have to be the same');
        $('#chpw-password').focus();
    } else {
        return true;
    }
    return false;
}

//Hide optional content
function hideAll() {
    //Keep grey screen visible, if error message is visible
    if(errorVisible){ hideIgnores.greyScreen = true; }
    //Hide user menu
    if(!hideIgnores.userMenu){ setUserMenuVisible(false); }
    hideIgnores.userMenu = false;
    //Hide modals
    if(!hideIgnores.registerModal){ setRegisterVisible(false); }
    hideIgnores.registerModal = false;
    if(!hideIgnores.chpwModal){ setChpwVisible(false); }
    hideIgnores.chpwModal = false;
    if(!hideIgnores.profileModal){ setProfileVisible(false); }
    hideIgnores.profileModal = false;
    //Tooltips
    if(!hideIgnores.profileTip){ setProfileTipVisible(false); }
    hideIgnores.profileTip = false;
    //GreyScreen
    hideIgnores.greyScreen = false;
}

$(document).ready(function() {

    /*******************/
    /** General Setup **/
    /*******************/

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
        //Error handling (hide if visible)
        setErrorVisible(false);
    }, function(evt){
        //Error handling
        setErrorVisible(true);
    });
    //Error Modal
    $('#error-submit').click(function(){
        $('#error-modal-load').removeClass('hidden');
        openRoom = 0; //Reopen room if reconnect successful
        api.reconnect();
    });
    //Visibility changes
    document.addEventListener('visibilitychange', function(){
        //Clear notify blinker if active
        if(!document.hidden && notify){
            notify = false;
            clearInterval(notifyInterval);
            document.title = 'Chat';
        }
    }, false);

    /*************************/
    /** Custom Api Handling **/
    /*************************/

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
                rooms[openRoom] = { msgs : [], counter : 0 };
                api.send(ApiRequest.OpenConversation, { c: openRoom });
            }
        }
    });
    //Login
    $('#toggle-login').click(function(){ setLoginVisible(!loginVisible); });
    $('#cancel-login').click(function(){ setLoginVisible(false); });
    $('#login-form').submit(function(){
        api.send(ApiRequest.Login, {username : $('#username').val().trim(), password : $('#password').val()});
        return false; //Prevent native submit
    });
    api.register(ApiRequest.Login, function(data){
        if(!data.s){ alert(data.error_text); }
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
    $('#user-menu').click(function(){ hideIgnores.userMenu = true; }); //Keep open => ignores html click
    //Logout
    $('#logout').click(function(){
        user.id = 0;
        user.name = null;
        api.send(ApiRequest.Logout, { sid: api.getSid() });
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
                $('#rooms').append('<a class="room" id="room-' + room.id + '" href="#' + room.title + '-' + room.id + '">' +
                    '<span id="room-counter-' + room.id + '"></span><span id="room-title-' + room.id + '"></span></a>');
                $('#room-title-' + room.id).text(room.title);
                //Open Public Conversation
                $('#room-' + room.id).click(function(inner){ return function(){
                    api.send(ApiRequest.OpenConversation, { c: inner.id });
                }}(room));
                //Add to internal data
                room.msgs = [];
                room.counter = 0;
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
            rooms[data.c].counter = 0;
            openRoom = data.c;
            $('#room-counter-' + data.c).text('');
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
        if(data.s){ receiveMessages(data.msgs, true); }
        else { alert(data.error_text); }
    });
    //Register
    $('#register').click(function(){
        setLoginVisible(false);
        setRegisterVisible(true);
    });
    $('#register-modal').click(function(){
        hideIgnores.registerModal = true;
        hideIgnores.greyScreen = true;
    });
    $('#register-modal-close').click(function(){ setRegisterVisible(false); });
    $('#register-cancel').click(function(){ setRegisterVisible(false); });
    $('#register-form').submit(function(){
        if(registerValid()){
            //Valid: Register
            api.send(ApiRequest.Register, {
                username: $('#register-username').val().trim(),
                email: $('#register-mail').val().trim(),
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
            $('#register-password').val('');
            $('#register-password-repeat').val('');
        } else {
            alert(data.error_text);
        }
    });
    //Change Password
    $('#chpw').click(function(){
        setUserMenuVisible(false);
        setChpwVisible(true);
    });
    $('#chpw-modal-close').click(function(){ setChpwVisible(false); });
    $('#chpw-cancel').click(function(){ setChpwVisible(false); });
    $('#chpw-modal').click(function(){
        hideIgnores.chpwModal = true;
        hideIgnores.greyScreen = true;
    });
    $('#chpw-form').submit(function(){
        if(chpwValid()){
            api.send(ApiRequest.ChangePassword, {
                oldpw: $('#chpw-old-password').val(),
                newpw: $('#chpw-password').val(),
            });
        }
        return false; //Prevent native submit
    });
    //Change Password (callback)
    api.register(ApiRequest.ChangePassword, function(data){
        if(data.s){
            alert('Password was successfully changed');
            setChpwVisible(false);
            $('#chpw-old-password').val('');
            $('#chpw-password').val('');
            $('#chpw-password-repeat').val('');
        } else {
            alert(data.error_text);
        }
    });
    //Change Profile
    $('#profile').click(function(){
        if(user.id == 0){ return false; }
        api.send(ApiRequest.GetUser, { userid: user.id });
        setUserMenuVisible(false);
        setProfileVisible(true);
    });
    $('#profile-modal-close').click(function(){ setProfileVisible(false); });
    $('#profile-cancel').click(function(){ setProfileVisible(false); });
    $('#profile-modal').click(function(){
        hideIgnores.profileModal = true;
        hideIgnores.greyScreen = true;
    });
    $('#profile-form').submit(function(){
        api.send(ApiRequest.ChangeProfile, {
            status: $('#profile-status').val(),
            description: $('#profile-description').val(),
        });
        return false; //Prevent native submit
    });
    //Change Progile (callbacks)
    api.register(ApiRequest.GetUser, function(data){
        if(data.s && data.users[0].id == user.id){
            $('#profile-status').val(data.users[0].status);
            $('#profile-description').val(data.users[0].description);
            $('#profile-status').prop('disabled', false);
            $('#profile-description').prop('disabled', false);
            if(profileVisible){ $('#profile-status').focus(); }
        }
    });
    api.register(ApiRequest.ChangeProfile, function(data){
        if(data.s){
            alert('Profile was successfully changed');
            setProfileVisible(false);
        } else {
            alert(data.error);
        }
    });
    //Profile Tooltip
    api.register(ApiRequest.GetUser, function(data){
        if(data.s && !profileVisible){
            $('#profile-tooltip-name').text(data.users[0].username);
            $('#profile-tooltip-status').text(!data.users[0].status ? 'No Status' : data.users[0].status);
            $('#profile-tooltip-description').text(!data.users[0].description ? 'No Description' : data.users[0].description);
            //Add line breaks
            $('#profile-tooltip-description').html(
                $('#profile-tooltip-description').html().replace(/\n/g, '<br />'));
            setProfileTipVisible(true);
        }
    });
    $('#profile-tooltip').click(function(){
        hideIgnores.profileTip = true;
    });
    $('#profile-tooltip-close').click(function(){
        setProfileTipVisible(false);
    });
    $('#chat').scroll(function(){
        setProfileTipVisible(false);
    });
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
