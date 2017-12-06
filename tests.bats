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
