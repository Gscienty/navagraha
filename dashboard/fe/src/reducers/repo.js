import {
    FUNC_REPO_LIST_RECEIVE_POST,
    FUNC_REPO_LIST_REQUEST_POST,
    FUNC_REPO_LIST_SET,
    FUNC_REPO_LIST_UNSET,

    GATEWAY_REPO_LIST_RECEIVE_POST,
    GATEWAY_REPO_LIST_REQUEST_POST,
    GATEWAY_REPO_LIST_SET,
    GATEWAY_REPO_LIST_UNSET
} from '../actions/repo';

const initState = {
    funcRepo: {
        state: FUNC_REPO_LIST_UNSET,
        repo: []
    },
    gatewayRepo: {
        state: GATEWAY_REPO_LIST_UNSET,
        repo: []
    }
};

export default function repoReduce(state = initState, action) {
    
    switch (action.type) {

        case FUNC_REPO_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            funcRepo: {
                state: FUNC_REPO_LIST_UNSET,
                repo: []
            }
        });

        case FUNC_REPO_LIST_REQUEST_POST:
            return Object.assign({}, state, {
            funcRepo: {
                state: FUNC_REPO_LIST_SET,
                repo: action.repo
            }
        });

        case GATEWAY_REPO_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            state: GATEWAY_REPO_LIST_SET,
            repo: action.repo
        });

        case GATEWAY_REPO_LIST_REQUEST_POST:
            return Object.assign({}, state, {
            state: GATEWAY_REPO_LIST_UNSET,
            repo: []
        })；

        default:
            return state;
    };
};

