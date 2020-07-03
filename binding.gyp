{
  "targets": [{
    "target_name": "db",
      "sources": [ "cpp/src/*.cpp", "cpp/src/*.hpp" ],

      "make_global_settings": [
        ["CC", 'usr/bin/clang'],
        ["CXX", "/usr/bin/clang++"],
        ["LINK", "/usr/bin/clang++"]
      ],

      "cflags_cc": ["-fexceptions", "-Wno-unused-result"],

      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ],

      "conditions": [
        ['OS=="mac"', {
          "cflags": ["-std=c++14x", "-Wall", "-pedantic", "-fexceptions" , "-Wno-unused-result"],

          "defines": [
            "__MACOSX_CORE__"
          ],

          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS": ["-std=c++14", "-Wno-unused-result"],
          }
        },

      "OS=='linux'", {
        "cflags": ['-std=c++14', "-Wall", "-fexceptions" , "-Wno-unused-result"],
      }
        ]
      ]
  }]
}



