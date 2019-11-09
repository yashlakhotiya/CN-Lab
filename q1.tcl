set ns [new Simulator]

$ns color 1 Blue

set nt [open "out.nam" w]
$ns namtrace-all $nt

set tr [open "trace.tr" w]
$ns trace-all $tr

proc finish {} {
	global ns nt tr
	$ns flush-trace
	close $nt
	close $tr
	exec nam out.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail

set udp [new Agent/UDP]
set null [new Agent/Null]

$ns attach-agent $n0 $udp
$ns attach-agent $n1 $null

$ns connect $udp $null

$udp set fid_ 1

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packetSize_ 1000
$cbr set rate_ 1Mb
$cbr set random_ false

$ns at 0.5 "$cbr start"
$ns at 1.0 "$cbr stop"
$ns at 1.2 "finish"

$ns run