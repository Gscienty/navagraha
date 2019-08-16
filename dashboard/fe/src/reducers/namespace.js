import {
    NAMESPACE_LIST_REQUEST_POST,
    NAMESPACE_LIST_RECEIVE_POST,
    NAMESPACE_LIST_ADDING_POST,
    NAMESPACE_LIST_DELETING_POST,
    NAMESPACE_LIST_UNSET,
    NAMESPACE_LIST_SET,
    NAMESPACE_SELECTED_SET,
    NAMESPACE_SELECTED_UNSET,
    NAMESPACE_SELECT_DISPLAY,
} from '../actions/namespace';

const initState = {
    state: NAMESPACE_LIST_UNSET,
    namespace: [],
    selectedState: NAMESPACE_SELECTED_UNSET,
    selectedNamespace: 'unset'
};

export default function namespaceReduce(state = initState, action) {

    switch (action.type) {

        case NAMESPACE_LIST_REQUEST_POST:
            return state;

        case NAMESPACE_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            state: NAMESPACE_LIST_SET,
            namespace: action.namespace
        });

        case NAMESPACE_LIST_ADDING_POST:
            return state;

        case NAMESPACE_LIST_DELETING_POST:
            return state;

        case NAMESPACE_SELECT_DISPLAY:
            return Object.assign({}, state, {
            selectedState: NAMESPACE_SELECTED_SET,
            selectedNamespace: action.namespace
        });

        default:
            return state;
    };
};
