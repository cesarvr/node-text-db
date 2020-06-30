{
  "targets": [
    {
      "target_name": "db",
      "sources": [ "cpp/src/*.cc", "cpp/src/*.hpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
