if [ "$1" == "double" ]; then
	find . -name "*.c" -o -name "*.cl" | xargs sed -i '' 's/float/double/g'
elif [ "$1" == "float" ]; then
	find . -name "*.c" -o -name "*.cl" | xargs sed -i '' 's/double/float/g'
fi
