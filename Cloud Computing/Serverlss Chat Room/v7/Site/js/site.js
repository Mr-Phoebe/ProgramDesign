var ChatApp = window.ChatApp || {};

(function scopeWrapper($) {

    var currentUsername = 'Student';

    var lastChat = null;

    var apiEndpoint = ChatApp.apiEndpoint;

    ChatApp.populateChats = function () {
        $.get(apiEndpoint + '/conversations').done(function (data) {
            data.forEach(function (convo) {
                var otherUsers = [];
                convo.participants.forEach(function (user) {
                    if (user !== currentUsername) {
                        otherUsers.push(user);
                    }
                });

                var last = '&nbsp;';
                if (convo.last) {
                    last = moment(new Date(convo.last)).fromNow();
                }

                $('TBODY').append('<tr><td><a href="chat.html#' + convo.id + '">' + otherUsers.join(', ') + '</a></td><td>' + last + '</td></tr>');
            });
            $('TBODY').append('<tr><td></td><td></td></tr>');
        });
    };

    ChatApp.loadChat = function () {
        $.get(apiEndpoint + '/conversations/' + location.hash.substring(1)).done(function (result) {
            var lastRendered = lastChat === null ? 0 : lastChat;
            if((lastChat === null && result.last) || lastChat < result.last) {
                lastChat = result.last;
            } else {
                return;
            }
            result.messages.forEach(function (message) {
                if(message.time > lastRendered) {
                    var panel = $('<div class="panel">');
                    if (message.sender === currentUsername) {
                        panel.addClass('panel-default');
                    } else {
                        panel.addClass('panel-info');
                        panel.append('<div class="panel-heading">' + message.sender + '</div>');
                    }
                    var body = $('<div class="panel-body">').text(message.message);
                    panel.append(body);
                    panel.append('<div class="panel-footer messageTime" data-time="' + message.time + '">' + moment(message.time).fromNow() + '</div>');

                    var row = $('<div class="row">');
                    var buffer = $('<div class="col-xs-4">');
                    var holder = $('<div class="col-xs-8">');
                    holder.append(panel);

                    if (message.sender === currentUsername) {
                        row.append(buffer);
                        row.append(holder);
                    } else {
                        row.append(holder);
                        row.append(buffer);
                    }

                    $('#chat').append(row);
                }
            });
            window.scrollTo(0, document.body.scrollHeight);
        });
    };

    ChatApp.send = function () {
        $.post(apiEndpoint + '/conversations/' + location.hash.substring(1), $('#message').val())
            .done(function () {
                $('#message').val('').focus();
                ChatApp.loadChat();
            });

    };

}(jQuery));