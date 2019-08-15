import {
    NAMESPACE_LIST_REQUEST_POST,
    NAMESPACE_LIST_RECEIVE_POST,
    NAMESPACE_LIST_ADDING_POST,
    NAMESPACE_LIST_DELETING_POST,
    NAMESPACE_LIST_UNSET,
    NAMESPACE_LIST_SET
} from '../actions/namespace';

const initState = {
    state: NAMESPACE_LIST_UNSET,
    namespace: []
}

export default function namespaceReduce(state = initState, action) {

    switch (action.type) {

        case NAMESPACE_LIST_REQUEST_POST:
            return Object.assign({}, state, {
                state: NAMESPACE_LIST_UNSET
            });

        case NAMESPACE_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
                state: NAMESPACE_LIST_SET,
                namespace: action.namespace
            });

        case NAMESPACE_LIST_ADDING_POST:
            return Object.assign({}, state, {
                state: NAMESPACE_LIST_UNSET
            });

        case NAMESPACE_LIST_DELETING_POST:
            return Object.assign({}, state, {
                state: NAMESPACE_LIST_UNSET
            });

        default:
            return state;
    }
}
