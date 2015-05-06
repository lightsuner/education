<?php foreach($data as $newItem): ?>
<li>
    <span class="date"><?php echo strftime('%d %B %Y', $newItem['created']); ?></span>
    <br />
    <a href="#"><?php echo $newItem['title']; ?></a>
</li>
<?php endforeach;?>