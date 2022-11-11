#!/bin/bash

meson setup builddir    -Dbuildtype=debug
meson setup builddiropt -Dbuildtype=debugoptimized
