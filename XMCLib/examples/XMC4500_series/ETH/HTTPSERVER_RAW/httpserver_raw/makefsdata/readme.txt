This directory contains a script ('makefsdata') to create C code suitable for
httpd for given html pages (or other files) in a directory (default is "fs" folder)

 Usage: makefsdata [targetdir] [-s] [-i] [-f:<filename>]

   targetdir: relative or absolute path to files to convert
   switch -s: toggle processing of subdirectories (default is on)
   switch -e: exclude HTTP header from file (header is created at runtime, default is off)
   switch -11: include HTTP 1.1 header (1.0 is default)
   switch -nossi: no support for SSI (cannot calculate Content-Length for SSI)
   switch -c: precalculate checksums for all pages (default is off)
   switch -f: target filename (default is "fsdata.dat")

   if targetdir not specified, makefsdata will attempt to
   process files in subdirectory 'fs'
   
After fsdata.dat is generated please copy it to the parent directory "httpserver_raw".
