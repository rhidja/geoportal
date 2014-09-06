(function($) {
	Drupal.behaviors.geoportal = {
		attach: function(context) {
			// En cliquant sur "détail" à la fin de la description d'une métatdonnées
			// ce fonction fait appel au menu "geoportal_detail" pour récupérer 
			// le détail d'une métadonnée et le charger avec la methode load de ajax
			// dans la 'div' qui à comme id '#geoContent'.
			$('.getDetail', context).click(function () {
				var id = $(this).attr("id");
				var url ="?q=geoportal_detail/"+id;
				$("#geoContent").load(url+" #mdDetails");
			});			
		}
	}
})(jQuery);