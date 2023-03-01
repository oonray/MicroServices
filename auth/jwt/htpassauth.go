package main

import (
	htpasswd "github.com/tg123/go-htpasswd"
)

var (
	Htfile *htpasswd.File
)

func Open() {
	Htfile = htpasswd.New(Args.Htpass_file, htpasswd.DefaultSystems, nil)
}

func Match(user string, pass string) error {
	return Htfile.Match(user, pass)
}
