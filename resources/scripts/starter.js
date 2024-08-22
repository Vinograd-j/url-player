function checkVideoReady() {

  var video = document.querySelector('video');

  if (document.readyState === 'complete')
  {
    if (video.paused)
    {
      video.play();
    }
  }else{
    setTimeout(checkVideoReady, DELAY_TIME);
  }

}

checkVideoReady();