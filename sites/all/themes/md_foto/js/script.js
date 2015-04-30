(function ($) {
	$(function(){

		$('.meta_share div').each(function() {
			var html = $(this).html();
			html = html.replace(/<\!--/g, '');
			html = html.replace(/-->/g, '');
			jQuery(this).html(html);
		});


        $('.node-photos-teaser').mouseenter(function() {
            $(this).addClass('photos-hover');
        }).mouseleave(function() {
            $(this).removeClass('photos-hover');
        });


    });
})(jQuery);