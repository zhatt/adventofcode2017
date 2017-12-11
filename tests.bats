#!/usr/bin/env bats

runcmd() {
    "$@" 2>/dev/null
}

runtest() {
	local testname=$1
	local day=${testname%%.*}
	run runcmd $BATS_TEST_DIRNAME/$testname < "$day.input"
        [[ $status -eq 0 ]]
	[[ $output == "$(< $testname.output)" ]]
}

@test "day1.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day1.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day2.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day2.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day3.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day3.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day4.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day4.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day5.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day5.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day6.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day6.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day7.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day7.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day8.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day8.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day9.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day9.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day10.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day10.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

day10_2_stdin_run() {
    echo "$1" | "$BATS_TEST_DIRNAME"/day10.2 2>/dev/null
}

@test "day10.2.1" {
	run day10_2_stdin_run ''
	[[ $status -eq 0 ]]
	[[ $output == 'a2582a3a0e66e6e86e3812dcb672a272' ]]
}

@test "day10.2.2" {
	run day10_2_stdin_run 'AoC 2017'
	[[ $status -eq 0 ]]
	[[ $output == '33efeb34ea91902bb2f59c9920caa6cd' ]]
}

@test "day10.2.3" {
	run day10_2_stdin_run '1,2,3'
	[[ $status -eq 0 ]]
	[[ $output == '3efbe78a8d82f29979031a4aa0b16a9d' ]]
}

@test "day10.2.4" {
	run day10_2_stdin_run '1,2,4'
	[[ $status -eq 0 ]]
	[[ $output == '63960835bcdc130f0b66d7ff4f6a5a8e' ]]
}

