SET DISPLAY=:0
echo SET DISPLAY=:0 >> %userprofile%\.bashrc
start /B "VcXsrv" "C:\Program Files\VcXsrv\vcxsrv.exe" -multiwindow -clipboard -wgl -ac
docker build -t smolrpg .
docker run --rm -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=host.docker.internal:0 --net=host smolrpg