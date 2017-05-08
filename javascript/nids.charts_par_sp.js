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
      $('#edit-espece, #edit-type-graph, #edit-annee').change(function(){
      	sp=$('#edit-espece').val();
      	type=$('#edit-type-graph').val();
      	annee=$('#edit-annee').val();
      	if (type=='indiv'){
      		titre='Individus observés'
      	}else{
			titre="Nombre d'observations"
      	}
      	indata={espece:sp,type_graph:type,annee:annee};
		$.ajax({
				url: "../nids/charts_par_sp_ajax", 
				data: indata, 
				type: "POST", 
				success: function(result){
						var data=[];
						var result=result;
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

					    $('#container_par_sp').highcharts({
					        title: {
					            text: titre,
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
					                text: 'Nombre d\'individus'
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
      })
    }
  };
}(jQuery));


