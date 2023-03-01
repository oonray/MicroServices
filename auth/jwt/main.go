package main

import (
	"flag"
	"fmt"
	"github.com/gin-gonic/gin"
)

type ARGS struct {
	Host        string
	Port        int
	Htpass_file string
}

var (
	Args   ARGS
	router *gin.Engine
)

func init() {
	flag.StringVar(&Args.Host, "H", "0.0.0.0", "The Host to bind to")
	flag.IntVar(&Args.Port, "P", 8080, "The Port to bind to")
	flag.StringVar(&Args.Htpass_file, "HP", "", "The path of a htpass file")
	flag.Parse()
}

func main() {
	router = gin.Default()
	router.Run(fmt.Sprintf("%s:%d", Args.Host, Args.Port))
}
