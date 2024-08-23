const toggleButton = document.querySelector('div.ytp-autonav-toggle-button');

const DELAY_TIME= 500;

function isAutoplayEnabled() {
    return toggleButton.getAttribute('aria-checked') === 'true';
}

function checkVideoReady() {
    var video = document.querySelector('video');
    if (video && video.readyState === 4) {
        if (isAutoplayEnabled())
            toggleButton.click();
    } else {
        setTimeout(checkVideoReady, DELAY_TIME);
    }
}

checkVideoReady();