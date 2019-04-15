# docker (misc 10)

The description of the challenge is pretty simple: _docker pull whowouldeverguessthis/public_.

Considering the low score of this chalenge, we assume that it's trivial, so get the image and grep for the flag format:

```sh
$ docker pull whowouldeverguessthis/public
[...]
$ docker images -q whowouldeverguessthis/public
969996089570
$ grep -r PCTF /var/lib//docker/image/overlay2/imagedb/content/sha256/969996089570*
{"architecture":"amd64","config":{"Hostname":"","Domainname":"","User":"","AttachStdin":false,"AttachStdout":false,"AttachStderr":false,"Tty":false,"OpenStdin":false,"StdinOnce":false,"Env":["PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"],"Cmd":["bash"],"ArgsEscaped":true,"Image":"sha256:476c8b6b6d9fcef1c0e7476342e47ca0b0480e44e5bb42ce94a4cc8415905413","Volumes":null,"WorkingDir":"","Entrypoint":null,"OnBuild":null,"Labels":null},"container":"f785c362a9cfec511ece69829f4bd20a2918a9e291fffe1e19f75485de4cd37b","container_config":{"Hostname":"","Domainname":"","User":"","AttachStdin":false,"AttachStdout":false,"AttachStderr":false,"Tty":false,"OpenStdin":false,"StdinOnce":false,"Env":["PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"],"Cmd":["/bin/sh","-c","echo \"I'm sorry, but your princess is in another castle\" \u003e /flag"],"ArgsEscaped":true,"Image":"sha256:476c8b6b6d9fcef1c0e7476342e47ca0b0480e44e5bb42ce94a4cc8415905413","Volumes":null,"WorkingDir":"","Entrypoint":null,"OnBuild":null,"Labels":null},"created":"2019-04-12T17:03:47.069664703Z","docker_version":"18.09.2","history":[{"created":"2019-01-22T19:22:38.494832817Z","created_by":"/bin/sh -c #(nop) ADD file:34b9952e66cb98287bc41fab82739375fe6c43f38ed3b893e98a99035b494770 in / "},{"created":"2019-01-22T19:22:38.706883433Z","created_by":"/bin/sh -c #(nop)  CMD [\"bash\"]","empty_layer":true},{"created":"2019-04-12T17:03:46.241744406Z","created_by":"/bin/sh -c echo \"PCTF{well_it_isnt_many_points_what_did_you_expect}\" \u003e /flag"},{"created":"2019-04-12T17:03:47.069664703Z","created_by":"/bin/sh -c echo \"I'm sorry, but your princess is in another castle\" \u003e /flag"}],"os":"linux","rootfs":{"type":"layers","diff_ids":["sha256:743aff3a80526229ca5762b3240e4e506b6b3a61e97accb853707a946a3abb39","sha256:a5fdd7807f999b258a273978509252fcdbb76218e14a01376d5b2ade4798826b","sha256:e958f8e060fc9bb06df3ccb0aff183fa8c549c369536f063d7ea36a617c86564"]}}
```

And we extract the flag from the image: `PCTF{well_it_isnt_many_points_what_did_you_expect}`
