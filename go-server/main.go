package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os/exec"
	"strconv"
	"strings"

	"github.com/gorilla/mux"
)

func memoryPage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*")
	fmt.Fprintf(w, getMemoryData())
}

func cpuPage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*")
	fmt.Fprintf(w, getCPUData())
}

func procsPage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*")
	fmt.Fprintf(w, getProcsData())
}

func killPage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*")
	path := strings.Split(r.URL.Path, "/")
	pid := path[2]
	fmt.Println(pid)
	cmd := exec.Command("bash", "-c", "kill "+pid)
	var out bytes.Buffer
	cmd.Stdout = &out
	err2 := cmd.Run()
	if err2 != nil {
		log.Fatal(err2)
	}
	fmt.Fprintf(w, "bien")
}

func handleRequests() {
	myRouter := mux.NewRouter()

	http.HandleFunc("/memory", memoryPage)
	http.HandleFunc("/cpu", cpuPage)
	http.HandleFunc("/procs", procsPage)
	myRouter.HandleFunc("/kill/{pid}", killPage)
	http.Handle("/", myRouter)
	log.Fatal(http.ListenAndServe(":10000", nil))
}

func check(e error) {
	if e != nil {
	}
}

func main() {
	handleRequests()
}

func getProcsData() string {
	files, err := ioutil.ReadDir("/proc/")
	if err != nil {
		log.Fatal(err)
	}

	cadena := ""
	for _, f := range files {
		if _, err := strconv.Atoi(f.Name()); err == nil {
			ruta := fmt.Sprintf("/proc/%s/stat", f.Name())
			dat, err := ioutil.ReadFile(ruta)
			check(err)
			arr := strings.Split(string(dat), " ")
			cadena = fmt.Sprintf("%s|%s,%s,%s,%s", cadena, arr[0], arr[1], arr[2], arr[3])
		}
	}
	return proc()
}

func getMemoryData() string {
	cmd := exec.Command("bash", "-c", "cat /proc/meminfo | grep 'MemTotal\\|Active:'")
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		log.Fatal(err)
	}
	return out.String()
}

func getCPUData() string {
	cmd := exec.Command("bash", "-c", "top -b -n 2 -d 0.1|grep Cpu")
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		log.Fatal(err)
	}
	arr := strings.Split(out.String(), ",")
	arr2 := strings.Split(arr[10], " ")
	f := arr2[1]
	s, err := strconv.ParseFloat(f, 32)
	return fmt.Sprintf("%f", 100-s)
}

func proc() string {
	cmd := exec.Command("bash", "-c", "ps -eo pid,comm,user,state,%mem,ppid")
	var out bytes.Buffer
	cmd.Stdout = &out
	err2 := cmd.Run()
	if err2 != nil {
		log.Fatal(err2)
	}
	return out.String()
}
