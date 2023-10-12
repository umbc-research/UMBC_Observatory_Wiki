PATH="/var/www/obs-web.rs.umbc.edu/data/pages/blog"
/bin/inotifywait -m -r -e create,delete "$PATH" |
	while read -r directory event file
	do
		echo "Change in $file was $event"
		./bin/blog "$file" "$event"
	done
