/*global jQuery, window, document, self, _gaq, Drupal, google */
(function($) {

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
		if($.isArray(self.val())) {
		  isval=self.val()[0];
 		}else{
		  isval=self.val();
		}
		if(isval !== "Autre" && isval !== "Inconnue" && isval !== ""){
			$.ajax({
				url: "nids/oiseaux_pics", 
				data: { oiseau : isval }, 
				type: "POST", 
				success: function(result){
					link=result['link'].replace('orig','580_360')
					$('#photodiv'+bid).html('<a href="'+result['link']+'" target="_blank"><img src="'+link+'" style="height:200px;"></a>')
					}
			})
		}else{
			$('#photodiv'+bid).html('<div id="photodiv0"style="display: none;">')
			
		};
      });
    }
  };

}(jQuery));