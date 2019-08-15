import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export REPO_REQUEST_POST = 'repo_request_post';
export function requestRepo() {
    return {
        type: REPO_REQUEST_POST,
        repo: []
    };
};

export REPO_RECEIVE_POST = 'repo_receive_post';
export function receiveRepo(received) {
    return {
        type: REPO_RECEIVE_POST,
        repo: received
    };
};

export REPO_UNSET = 'repo_unset';
export REPO_SET = 'repo_set';

export function fetchRepo() {

    return function(dispatch) {
        dispatch(requestRepo());

        return fetch(`{PREFIX_URI}/api/repo`)
            .then(response => response.json())
            .then(json => dispatch(receiveRepo(json)));
    };
};
