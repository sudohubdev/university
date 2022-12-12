var isResizing = false;

document.addEventListener("DOMContentLoaded", function() {
    var container = document.querySelector(".container");
    left = document.querySelector(".code"),
        right = document.querySelector(".chart"),
        handle = document.querySelector(".drag");

    handle.onmousedown = function(e) {
        isResizing = true;
    };

    document.onmousemove = function(e) {
        // we don't want to do anything if we aren't resizing.
        if (!isResizing) {
            return;
        }

        var offsetRight = container.clientWidth - (e.clientX - container.offsetLeft);

        if (offsetRight < document.body.clientWidth / 5) {
            return false;
        }
        left.style.right = offsetRight + "px";
        right.style.width = offsetRight + "px";
    }

    document.onmouseup = function(e) {
        // stop resizing
        isResizing = false;
    }
})