/*global jQuery, window, document, self, _gaq, Drupal, google */
(function($) {

drupal_set_message('here', 'status');

  Drupal.behaviors.nids_map = {

    map: {}, map_center: {}, marker_icon: {}, polygon_icon: {},
    markers: [], polygons: [], polygon_vertices: [],
    geography: "", infowindows: [],

    attach: function() {
      this.attachEvents();
    },

    attachEvents: function() {
      polygon = {};
      $("[name^=espece_]").change(function() {
        self=$(this);
        bid=$(this).attr('name').replace('espece_', '');
        bid=bid.replace('[]','');
        $.ajax({
          url: "nids/oiseaux_pics",
          data: { oiseau : self.val()[0] },
          type: "POST",
          success: function(result){
              link=result['link'].replace('orig','580_360')
              $('#photodiv'+bid).html('<a href="'+result['link']+'" target="_blank"><img src="'+link+'" style="height:200px;"></a>')
          }
        });
      });
    }
  };

}(jQuery));