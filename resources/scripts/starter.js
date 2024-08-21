const DELAY_TIME = 500;

function checkVideoReady() {
  var video = document.querySelector('video');
  if (video && video.readyState === 4) {  // VIDEO_READY_STATE_HAVE_ENOUGH_DATA
    video.play();
  } else {
    setTimeout(checkVideoReady, DELAY_TIME);
  }
}
checkVideoReady();