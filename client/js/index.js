var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    loginVisible = visible;
}

$(document).ready(function() {
    api.connect(function(){
        //api.send({ t: 11, username: 'JP', password: '' });
    });
    $('#toggle-login').click(function(){ setLoginVisible(!loginVisible); });
    $('#cancel-login').click(function(){ setLoginVisible(false); });
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
