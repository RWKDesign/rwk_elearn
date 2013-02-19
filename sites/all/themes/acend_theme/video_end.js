
(function ($) {

  Drupal.behaviors.videoEnd = {
    attach: function (context, settings) {
      $('.vjs-tech', context).onended(function () {
        $(this).alert('whoohaa');
      });
    }
  };

})(jQuery);
