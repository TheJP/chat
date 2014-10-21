var api = {
    wsUri : 'ws://127.0.0.1:8080', //Testing environment
    sid : null,
    ws : null,
    ready : false
};
api.setSid = function(sid){
    api.sid = sid;
    var expire = new Date();
    expire.setTime(expire.getTime() + 31536000000);  //Exactly 1 year (value in ms)
    document.cookie = 'sid=' + escape(sid) + '; expires=' + expire.toGMTString();
};
api.getSid = function (){
    //Is the session id already set?
    if(api.sid == null){
        //No: Try reading it from the cookies
        var start, end;
        start = document.cookie.indexOf('sid=');
        if(start < 0){ return null; } else { start += 4; }
        end = document.cookie.indexOf(';', start);
        if(end < 0){ end = document.cookie.length; }
        api.sid = document.cookie.substring(start, end);
    }
    return api.sid;
};
api.connect = function(callback){
    if(api.ws == null){
        api.ws = new WebSocket(api.wsUri);
        api.ws.onopen = function(evt){ api.ready = true; if(callback){ callback(); } };
        api.ws.onclose = function(evt){ api.ready = false; api.ws = null; };
        api.ws.onmessage = function(evt){ api.handle(evt) };
        api.ws.onerror = function(evt){ alert('error: ' + evt.data); };
    }
};
api.disconnect = function(){
    if(api.ws != null){
        api.ready = false;
        api.ws.close();
        api.ws = null;
    }
};
api.send = function(obj){
    if(api.ws != null && api.ready){
        var message = JSON.stringify(obj);
        api.ws.send(message);
    }
}
api.handle = function(evt){
    alert('message: ' + evt.data);
}
