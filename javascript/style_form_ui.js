(function($) {
	Drupal.behaviors.nids = {

    attach: function() {
		$('input[type=text]').button().css({
			'font' : 'inherit',
			'color' : 'inherit',
			'text-align' : 'left',
			'outline' : 'none',
			'cursor' : 'text'
		});
		//$('select').menu().css({'display':'block','margin-bottom:20px'});
		$('input[type=submit]').button();
	}
	}
}
(jQuery));

