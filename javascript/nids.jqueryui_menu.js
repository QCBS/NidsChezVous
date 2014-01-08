/*global jQuery, window, document, self, _gaq, Drupal, google */
(function($) {

  Drupal.behaviors.nids_jqueryui_menu = {

    attach: function() {
      $('button').button();
      $('input[type="submit"]').button();
      $('#edit-submit').button();
      $('#block-system-main ul.menu li').button().css({
        'width':'300px','list-style-type':'none','padding':'5px','margin':'5px'}
        );
      $('.ui-button-text').click(function(){
         window.location = $(this).children("a").attr('href');
      })
    },
  }
}(jQuery));