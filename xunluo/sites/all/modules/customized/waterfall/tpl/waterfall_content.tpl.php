
<div id="container" class="transitions-enabled infinite-scroll clearfix">
<?php 
global $pager_total;
foreach($rows as $data){?>
<div class="box col3">
   <h5><?php print l($data['title'], 'node/'.$data['nid']); ?></h5>
   <div class="box-content">
       <p class="thum">    
             <?php print l('<img src="'.image_style_url('pin', $data['uri']).'">', 'node/'.$data['nid'], array('html'=>true)); ?>
       </p>
       <p class="txt">    
            <?php print $data['teaser']; ?>
       </p>
   </div>    
</div>
<?php }?>
</div>
<script>
  jQuery(function(){
    
    var $container = jQuery('#container');
    
    $container.imagesLoaded(function(){
      $container.masonry({
        itemSelector: '.box',
        columnWidth: 100
      });
    });
		//var curPage = 0;
		//var pagesNum = 20;
		
			var curPage = 0;
			var pagesNum = <?php print $pager_total[0];?>;   // Number of pages
    $container.infinitescroll({
      navSelector  : '.pager',    // selector for the paged navigation 
      nextSelector : '.pager  a.active',  // selector for the NEXT link (to page 2)
      itemSelector : '.box',     // selector for all items you'll retrieve
			debug: true,
      loading: {
          finishedMsg: 'No more pages to load.',
          img: 'http://i.imgur.com/6RMhx.gif'
					//img:'http://www.infinite-scroll.com/loading.gif'
        },
			state: {
					currPage: 0 //关键
			}
      },

      // trigger Masonry as a callback
      function( newElements ) {
				curPage++;
				if(curPage == pagesNum || curPage > pagesNum){
					var $newElems = jQuery( newElements ).css({ opacity: 0 });
				}
				else{
				// hide new items while they are loading
        var $newElems = jQuery( newElements ).css({ opacity: 0 });
        // ensure that images load before adding to masonry layout
        $newElems.imagesLoaded(function(){
          // show elems now they're ready
          $newElems.animate({ opacity: 1 });
          $container.masonry( 'appended', $newElems, true ); 
        });
				}
						
					//默认方式	
        // hide new items while they are loading
        //var $newElems = jQuery( newElements ).css({ opacity: 0 });
        // ensure that images load before adding to masonry layout
        //$newElems.imagesLoaded(function(){
          // show elems now they're ready
          //$newElems.animate({ opacity: 1 });
          //$container.masonry( 'appended', $newElems, true ); 
        //});
      }
    );
    
  });
</script>