#!/bin/bash

cmake --build "${0%/*}/../cmake-build-debug" --target SoteriaServer -j 6

