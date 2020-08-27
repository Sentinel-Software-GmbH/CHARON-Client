pipeline {
    agent any
    environment {
        scmUrl = 'http://sentinel-server:7990/scm/chr/uds_client.git'
        serverPort = '7990'
    }
    stages {
        stage('Prepare Workspace') {
            steps {
                bat 'ceedling clean'
            }
        }

        stage('build') {
            steps {
                bat 'ceedling build'
            }
        }

        stage ('test') {
            steps {
                parallel (
                    "unit tests": { 
                        bat 'ceedling gcov:all'
                        bat 'ceedling utils:gcov'
                        xunit([Custom(customXSL: 'toolchain/ceedling/unity.xsl', deleteOutputFiles: true, failIfNotNew: true, pattern: 'build/artifacts/gcov/report.xml', skipNoTestFiles: false, stopProcessingIfError: true)])
                        cobertura coberturaReportFile: 'build/artifacts/gcov/GcovCoverageResults.xml'
                    },
                    //"integration tests": { bat 'cd src\\Ports\\Windows && ceedling build release && cd build\\artifacts\\release && call charon_client.exe' }
                )
            }
        }

        stage ('post-build') {
            steps {
                parallel (
                    "doxygen": {
                        bat 'doxygen'
                        
                    }
                )
            }
        }
    }
    post {
        success {
            archiveArtifacts 'build/documentation/html/Charon_UDS_Client.chm'
        }
        failure {
            mail to: 'inacio.steven@sentinelsw.de', subject: 'Pipeline failed', body: "${env.BUILD_URL}"
        }
    }
}