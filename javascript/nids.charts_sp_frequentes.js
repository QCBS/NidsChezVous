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
				url: "../nids/charts_sp_frequentes_ajax", 
				data: {chart:'indiv'}, 
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

					    $('#container_nbre_indiv').highcharts({
					        title: {
					            text: 'Individus observés à chaque semaine (10 espèces plus fréquentes)',
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
			$.ajax({
				url: "../nids/charts_sp_frequentes_ajax", 
				data: {chart:'obs'}, 
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

					    $('#container_nbre_espece').highcharts({
					        title: {
					            text: 'Nombre d\'observations à chaque semaine (10 espèces plus fréquentes)',
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
					                text: 'Nombre d\'observations'
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
				url: "../nids/charts_sp_frequentes_ajax", 
				data: {chart:'bar_freq'}, 
				type: "POST", 
				success: function(result){
						var data=[];
						var oiseaux=[];
						$.each(result,function(){
							data.push(parseInt(this.nbre));
							oiseaux.push(this.oiseau_espece);
						});

					    $('#container_nbre_obs_bar').highcharts({
						    chart: {
					            type: 'column'
					        },
					        title: {
					            text: 'Oiseaux les plus fréquemment observés'
					        },
					        xAxis: {
					            categories: oiseaux
					        },
					        yAxis: {
					            min: 0,
					            title: {
					                text: 'Nombre'
					            }
					        },
							colors: ['#7bb9e0'],
					        plotOptions: {
					            column: {
					                pointPadding: 0.2,
					                borderWidth: 0
					            }
					        },
					        series: [{
					        	name:"Espèces",
            					data:data
            				}]
					    });
			}
		});


			$.ajax({
				url: "../nids/charts_sp_frequentes_ajax", 
				data: {chart:'bar_nbre'}, 
				type: "POST", 
				success: function(result){
						var data=[];
						var oiseaux=[];
						$.each(result,function(){
							data.push(parseInt(this.nbre));
							oiseaux.push(this.oiseau_espece);
						});

					    $('#container_nbre_indiv_bar').highcharts({
						    chart: {
					            type: 'column'
					        },
					        title: {
					            text: 'Oiseaux avec le plus grand nombre d\'individus observés'
					        },
					        xAxis: {
					            categories: oiseaux
					        },
					        yAxis: {
					            min: 0,
					            title: {
					                text: 'Nombre'
					            }
					        },
							colors: ['#f9b53f'],
					        plotOptions: {
					            column: {
					                pointPadding: 0.2,
					                borderWidth: 0
					            }
					        },
					        series: [{
					        	name:"Espèces",
            					data:data
            				}]
					    });
			}
		});


    }
  };
}(jQuery));


