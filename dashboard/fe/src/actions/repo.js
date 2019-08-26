import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const FUNC_REPO_LIST_REQUEST_POST = 'func_repo_list_request_post';
export function requestFuncRepoList() {
    return {
        type: FUNC_REPO_LIST_REQUEST_POST,
        repo: []
    };
};

export const FUNC_REPO_LIST_RECEIVE_POST = 'func_repo_list_receive_post';
export function receiveFuncRepoList(received) {
    return {
        type: FUNC_REPO_LIST_RECEIVE_POST,
        repo: received
    };
};

export const FUNC_REPO_LIST_UNSET = 'func_repo_list_unset';
export const FUNC_REPO_LIST_SET = 'func_repo_list_set';

export function fetchFuncRepoList() {

    return function(dispatch) {
        dispatch(requestFuncRepoList());

        return fetch(`${PREFIX_URI}/api/repo/func`)
        .then(response => response.json())
        .then(json => dispatch(receiveFuncRepoList(json)));
    };
};

export const GATEWAY_REPO_LIST_REQUEST_POST = 'gateway_repo_list_request_post';
export function requestGatewayRepoList() {
    return {
        type: GATEWAY_REPO_LIST_REQUEST_POST,
        repo: []
    };
};

export const GATEWAY_REPO_LIST_RECEIVE_POST = 'gateway_repo_list_receive_post';
export function receiveGatewayRepoList(received) {
    return {
        type: GATEWAY_REPO_LIST_RECEIVE_POST,
        repo: received
    };
};

export const GATEWAY_REPO_LIST_UNSET = 'gateway_repo_list_unset';
export const GATEWAY_REPO_LIST_SET = 'gateway_repo_list_set';
export function fetchGatewayRepoList() {

    return function (dispatch) {
        dispatch(requestGatewayRepoList());

        return fetch(`${PREFIX_URI}/api/repo/apigw`)
        .then(response => response.json())
        .then(json => dispatch(receiveGatewayRepoList(json)));
    };
};

export function deleteRepo(name, version) {
    return function (dispatch) {
        return fetch(`${PREFIX_URI}/api/repo/remove/${name}/${version}`, {
            method: 'DELETE',
            credentials: 'include'
        });
    }
}
