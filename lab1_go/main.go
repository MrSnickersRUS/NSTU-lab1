package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	filePath := flag.String("file", "", "Путь к файлу данных")
	query := flag.String("query", "", "Команда для выполнения")
	flag.Parse()

	if *filePath == "" || *query == "" {
		fmt.Fprintf(os.Stderr, "Использование: %s --file <путь_к_файлу> --query '<команда>'\n", os.Args[0])
		os.Exit(1)
	}

	if err := ProcessQuery(*query, *filePath); err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
}
