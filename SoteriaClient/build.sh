#!/bin/bash

cmake --build "${0%/*}/../cmake-build-debug" --target SoteriaClient -j 6

