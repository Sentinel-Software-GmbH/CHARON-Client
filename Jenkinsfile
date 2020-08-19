pipeline {
    agent any
    environment {
        branch = 'master'
        scmUrl = 'http://sentinel-server:7990/scm/chr/uds_client.git'
        serverPort = '7990'
    }
    stages {
        stage('checkout git') {
            steps {
                // TODO Credentials
                git branch: branch, credentialsId: 'GitCredentials', url: scmUrl
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
                    "unit tests": { bat 'ceedling' },
                    "integration tests": { bat 'cd src\\Ports\\Windows && ceedling build release && cd build\\artifacts\\release && call charon_client.exe' }
                )
            }
        }
    }
    post {
        failure {
            mail to: 'inacio.steven@sentinelsw.de', subject: 'Pipeline failed', body: "${env.BUILD_URL}"
        }
    }
}