<?php if( isset($content) && !empty($content) ): ?>
  <section class="banner">
    <div class="row">
      <div class="col-12">
        <div class="row justify-content-center">
          <?php foreach($content as $nid => $field): ?>
            <div class="nota">
              <h3><?php print $field['title']; ?></h3>
              <p><?php print $field['desc']; ?></p>
              <img src="<?php print $field['img']; ?>" alt="$field['title']; ?>">              
            </div>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </section>
<?php endif; ?>
