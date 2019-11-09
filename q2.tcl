set ns [new Simulator]

$ns color 1 Blue

set nt [open "out.nam" w]
$ns namtrace-all $nt

set tr [open "trace.tr" w]
$ns trace-all $tr

proc finish {} {
	global ns tr nt
	$ns flush-trace
	close $nt
	close $tr
	exec nam out.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]

$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $sink

$ns connect $tcp $sink

$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

$ns at 0.1 "$ftp start"
$ns at 0.5 "$ftp stop"
$ns at 0.6 "finish"

$ns run