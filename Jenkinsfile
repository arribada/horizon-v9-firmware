pipeline {
    agent {
        label 'master'
    }

    environment {
        // Add custom tools to system path
        GCC_ARM_HOME = tool name: 'gcc_arm_none_eabi_7_2018_q2_update', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
        CMAKE_HOME = tool name: 'cmake_3_13_3', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
        CPPCHECK_HOME = tool name: 'cppcheck_1_87', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
        PATH = "${GCC_ARM_HOME}:${CMAKE_HOME}:${CPPCHECK_HOME}:$PATH"
    }

    stages {
        stage ('Compile Bootloader') {
            steps {
                sh 'git clean -fdx'
                sh 'make -C ports/nrf52840/bootloader'
                // Append the git commit details to the filename names
                sh '''
                    folder=ports/nrf52840/bootloader/build/
                    for file in $folder*.hex $folder*.bin $folder*.map ; do
                        basename=${file%.*}
                        extension=${file##*.}
                        mv "$file" "$basename"_"$(git describe --always --tags).$extension" || true
                    done
                '''
            }
            post { 
                success { 
                archiveArtifacts 'ports/nrf52840/bootloader/build/*.hex,ports/nrf52840/bootloader/build/*.map'
                }
            }
        }

        stage ('Compile Firmware') {
            steps {
                sh 'make -C ports/nrf52840'
                sh 'make -C ports/nrf52840 dfu_package'
                sh 'make -C ports/nrf52840 RELEASE=1'
                sh 'make -C ports/nrf52840 dfu_package RELEASE=1'
                // Append the git commit details to the filename names
                sh '''
                    folder=ports/nrf52840/build/
                    for file in $folder*.hex $folder*.bin $folder*.map $folder*.out $folder*.zip ; do
                        basename=${file%.*}
                        extension=${file##*.}
                        mv "$file" "$basename"_"$(git describe --always --tags).$extension" || true
                    done
                '''
            }
            post { 
                success { 
                archiveArtifacts 'ports/nrf52840/build/*.hex,ports/nrf52840/build/*.bin,ports/nrf52840/build/*.map,ports/nrf52840/build/*.out,ports/nrf52840/build/*.zip'
                }
            }
        }

        stage ('Compile Unit Tests') {
            steps {
                sh '''
                cd tests
                bash ./build_tests.sh
                '''
            }
        }

        stage ('Run Unit Tests') {
            steps {
                sh '''
                cd tests
                bash ./run_tests.sh --intensive
                '''
            }
        }

        stage ('Run Static Analysis Tools') {
            steps {
                sh '''
                # Run cppcheck
                cd ports/nrf52840
                make cppcheck
                # Rename all file locations to be at root directory
                sed -i 's%\\(<location file="\\)%\\1ports/nrf52840/%' cppcheck.xml
                cd ../..
    
                # Generate the test coverage file for the Cobertura report
                gcovr -r $WORKSPACE -e 'tests/' --xml > coverage.xml
                '''

                // Publish reports from static analysis tools
                recordIssues(tools: [cppCheck(pattern: 'ports/nrf52840/cppcheck.xml'), taskScanner(includePattern: '**/*.c,**/*.cpp,**/*.h', excludePattern: '**/ports/nrf52840/drivers/nRF5_SDK_15.2.0/**,**/tests/src/cmock/**,**/tests/src/googletest-release-1.8.1/**', lowTags: 'WARN', normalTags: 'TODO', highTags: 'FIXME')])
                xunit thresholds: [failed(unstableNewThreshold: '0', unstableThreshold: '0')], tools: [CTest(deleteOutputFiles: true, failIfNotNew: true, pattern: 'tests/src/build/Testing/**/Test.xml', skipNoTestFiles: false, stopProcessingIfError: true)]
                cobertura autoUpdateHealth: false, autoUpdateStability: false, coberturaReportFile: '**coverage.xml', conditionalCoverageTargets: '70, 0, 0', failUnhealthy: false, failUnstable: false, lineCoverageTargets: '80, 0, 0', maxNumberOfBuilds: 0, methodCoverageTargets: '80, 0, 0', onlyStable: false, sourceEncoding: 'ASCII', zoomCoverageChart: false
            }
        }
    }
}