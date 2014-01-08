/*global jQuery, window, document, self, _gaq, Drupal, google */
(function($) {

  Drupal.behaviors.nids_jqueryui = {

    attach: function() {
      $('button').button();
      $('input[type="submit"]').button();
      $('#edit-submit').button();
      $('select').not($("[id^=edit-espece]")).selectBoxIt({theme:'jqueryui'});
      $('[id^=edit-espece]').click(function(){
        $('option:selected',this).siblings().removeAttr("selected");
      });
      $("#myList li").click(function() {
        $(this).addClass("selected").siblings().removeClass("selected");
      });
      $('input[type=text]').button().css({
      'font' : 'inherit',
      'color' : 'inherit',
      'text-align' : 'left',
      'outline' : 'none',
      'cursor' : 'text'
    });
      $('#block-system-main ul.menu').menu().css({'width':'300px','list-style-type':'none'});
    },
  }
}(jQuery));