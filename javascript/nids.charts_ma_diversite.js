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
			$.ajax({
				url: "../nids/charts_ma_diversite_ajax", 
				data: {graph:'especes'}, 
				type: "POST", 
				success: function(result){
						var data=[];
						$.each(result,function(){
							var times=[];
							$.each(this.data,function(){
								times.push([Date.parse(this[0]),parseInt(this[1])]);
							});
							var tmp=[];
							tmp.name=this.name;
							tmp.data=times;
							data.push(tmp);
						});

					    $('#container_especes').highcharts({
					        title: {
					            text: 'Nombre d\'espèces observées',
					            x: -20 //center
					        },
					        subtitle: {
					            text: '',
					            x: -20
					        },
					        xAxis: {
					            type: 'datetime',
					            minRange: 7 * 24 * 3600000 // fourteen days
					        },
					        yAxis: {
					            title: {
					                text: 'Nombre'
					            },
					            plotLines: [{
					                value: 0,
					                width: 1,
					                color: '#808080'
					            }]
					        },
					        tooltip: {
					            valueSuffix: ''
					        },
					        legend: {
					            layout: 'vertical',
					            align: 'right',
					            verticalAlign: 'middle',
					            borderWidth: 0
					        },
				 			series: data
					    });
			}
		});
			$.ajax({
				url: "../nids/charts_ma_diversite_ajax", 
				data: {graph:'heures'}, 
				type: "POST", 
				success: function(result){
						var data=[];
						$.each(result,function(){
							var times=[];
							$.each(this.data,function(){
								times.push([Date.parse(this[0]),parseInt(this[1])]);
							});
							var tmp=[];
							tmp.name=this.name;
							tmp.data=times;
							data.push(tmp);
						});

					    $('#container_heures').highcharts({
					        title: {
					            text: 'Nombre de minutes passées à faire des observations',
					            x: -20 //center
					        },
					        subtitle: {
					            text: '',
					            x: -20
					        },
					        xAxis: {
					            type: 'datetime',
					            minRange: 7 * 24 * 3600000 // fourteen days
					        },
					        yAxis: {
					            title: {
					                text: 'Nombre'
					            },
					            plotLines: [{
					                value: 0,
					                width: 1,
					                color: '#808080'
					            }]
					        },
					        tooltip: {
					            valueSuffix: ''
					        },
					        legend: {
					            layout: 'vertical',
					            align: 'right',
					            verticalAlign: 'middle',
					            borderWidth: 0
					        },
				 			series: data
					    });


			}
		});
    }
  };
}(jQuery));


