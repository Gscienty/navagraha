import fetch from 'cross-fetch';
import { PREFIX_URI } from './common'

export const NAMESPACE_LIST_REQUEST_POST = 'namespace_request_post';
export function requestNamespaces() {
    return {
        type: NAMESPACE_LIST_REQUEST_POST,
        namespaces: []
    };
};

export const NAMESPACE_LIST_RECEIVE_POST = 'namespace_receive_post';
export function receiveNamespaces(received) {
    return {
        type: NAMESPACE_LIST_RECEIVE_POST,
        namespaces: received
    };
};

export function fetchNamespaces() {

    return function (dispatch) {
        dispatch(requestNamespaces());

        return fetch(`${PREFIX_URI}/api/namespace`)
            .then(response => response.json(), error => console.log('An error occurred.', error))
            .then(json => dispatch(receiveNamespaces(json)));
    }
};
