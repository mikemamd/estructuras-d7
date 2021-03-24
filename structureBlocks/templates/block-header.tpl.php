<section class="banner">
  <div class="row">
    <div class="col-12">
      <div class="row justify-content-center">
        <?php if( isset($content['title']) && !empty($content['title']) ): ?>
          <h1><?php print $content['title']; ?></h1>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="row">
    <div class="col-12">
      <div class="row justify-content-center">
        <?php if( isset($content['body']) && !empty($content['body']) ): ?>
          <p><?php print $content['body']; ?></p>
        <?php endif; ?>
      </div>
    </div>
  </div>
</section>
