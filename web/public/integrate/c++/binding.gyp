{
  "targets": [
    {
      "target_name": "standalone",
      "type": "executable",
      "sources": ["test.cpp"],
      "cflags": ["-Wall", "-std=c++11"],
      "include_dirs" : ["./"],
      "conditions": [
        [ "OS=='mac'", {
            "xcode_settings": {
                "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++"],
                "OTHER_LDFLAGS": ["-stdlib=libc++"],
                "MACOSX_DEPLOYMENT_TARGET": "10.7" }
            }
        ]
      ]
    }
  ]
}