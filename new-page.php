<div class="nav navbar-nav" id="dw__addnewpage">
    <a href="javascript:void(0);" id="createBlog" class="btn btn-primary" role="button" title="<?php echo tpl_getLang('add_new_page'); ?>">
        <?php echo iconify('mdi:file-plus'); ?>
    </a>
</div>

<script>
	function createBlogOnClick(){
	const url='obs-web.rs.umbc.edu/lib/tpl/bootstrap3/tpl/add-blog.php';
	var blogUrl='doku.php?id=blog:';

        fetch('lib/tpl/bootstrap3/tpl/add-blog.php')
		.then(response => response.text())
		.then(data => {
		    blogUrl += data;
		    window.location.assign(blogUrl);
		})
	}

document.getElementById('createBlog').addEventListener('click', createBlogOnClick);
</script>
