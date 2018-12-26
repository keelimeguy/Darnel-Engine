all: glew/.dummy

glew/.dummy:
	@cd glew/auto; \
	"bin/update_ext.sh" extensions/gl registry/gl/specs blacklist; \
	python bin/parse_xml.py registry/xml/egl.xml --core core/gl --extensions extensions/gl; \
	"bin/filter_gl_ext.sh"     extensions/gl; \
	find core/gl -maxdepth 1 -type f | grep -v VERSION | grep -v "~" | xargs cp --target-directory=extensions/gl; \
	touch extensions/gl/.dummy

	@touch glew/.dummy
