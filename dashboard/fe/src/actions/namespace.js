import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const NAMESPACE_LIST_REQUEST_POST = 'namespace_request_post';
export function requestNamespaces() {
    return {
        type: NAMESPACE_LIST_REQUEST_POST,
        namespace: []
    };
};

export const NAMESPACE_LIST_RECEIVE_POST = 'namespace_receive_post';
export function receiveNamespaces(received) {
    return {
        type: NAMESPACE_LIST_RECEIVE_POST,
        namespace: received
    };
};

export const NAMESPACE_LIST_ADDING_POST = 'namespace_adding_post';
export function addingNamespace() {
    return {
        type: NAMESPACE_LIST_ADDING_POST
    };
};

export const NAMESPACE_LIST_DELETING_POST = 'namespace_deleting_post';
export function deletingNamespace() {
    return {
        type: NAMESPACE_LIST_DELETING_POST
    };
};

export const NAMESPACE_LIST_UNSET = 'namespace_unset';
export const NAMESPACE_LIST_SET = 'namespace_set';
export function fetchNamespaces(check_cb) {

    return function (dispatch) {
        dispatch(requestNamespaces());

        return fetch(`${PREFIX_URI}/api/namespace`)
        .then(response => response.json(), error => console.log('An error occurred.', error))
        .then(json => {
            dispatch(receiveNamespaces(json));
            check_cb && check_cb();
        });
    };
};

export function addNamespace(name) {

    return function (dispatch) {
        dispatch(addingNamespace());

        return fetch(`${PREFIX_URI}/api/namespace`, {
            method: 'POST',
            credentials: 'include',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ namespace: name })
        })
        .then(response => dispatch(fetchNamespaces()));
    };
};

export function deleteNamespace(name) {
    return function (dispatch) {
        dispatch(deletingNamespace());

        return fetch(`${PREFIX_URI}/api/namespace/${name}`, {
            method: 'DELETE',
            credentials: 'include'
        })
        .then(response => dispatch(fetchNamespaces()));
    };
};

export const NAMESPACE_SELECTED_SET = 'namespace_selected_set';
export const NAMESPACE_SELECTED_UNSET = 'namespace_selected_unset';
export const NAMESPACE_SELECT_DISPLAY = 'namespace_select_display';
export function selectDisplayNamespace(namespace) {
    return {
        type: NAMESPACE_SELECT_DISPLAY,
        namespace: namespace
    };
};

export function addNamespaceGateway(namespace, gatewayRepo, policy) {
    return function(dispatch) {
        return fetch(`/api/gateway/${namespace}`, {
            method: 'POST',
            credentials: 'includes',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                namespace: namespace,
                policy: policy,
                replicas: 1,
                image: gatewayRepo
            })
        })
        .then(response => dispatch(fetchNamespaces()));
    };
};

export function deleteNamespaceGateway(namespace) {
    return function (dispatch) {
        return fetch(`/api/gateway/${namespace}`, {
            method: 'DELETE',
            credentials: 'includes',
        })
        .then(response => dispatch(fetchNamespaces()));
    }
}

