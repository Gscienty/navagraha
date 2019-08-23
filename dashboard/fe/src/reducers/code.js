import {
    CODE_TEMPLATE_LIST_RECEIVE_POST,
    CODE_TEMPLATE_LIST_REQUEST_POST,

    CODE_TEMPLATE_RECEIVE_POST,
    CODE_TEMPLATE_REQUEST_POST,

    CODE_TEMPLATE_LIST_SET,
    CODE_TEMPLATE_LIST_UNSET,

    CODE_TEMPLATE_SELECTED_SET,
    CODE_TEMPLATE_SELECTED_UNSET,
    
    CODE_SUBMIT_TOGGLE,

    CODE_RESET_METADATA,
    CODE_SUBMIT_METADATA,
    CODE_METADATA_SET,
    CODE_METADATA_UNSET,
    
    CODE_SUBMIT_SET,
    CODE_SUBMIT_UNSET,
    CODE_SUBMIT_CODE_INFO,
    CODE_RESET_CODE_INFO,

    CODE_BUILD_RUNNING,
    CODE_BUILD_WAITING,
    CODE_BUILDING_RUNNING,
    CODE_BUILDING_FINISHED,
    CODE_BUILDING_PROCESS
} from '../actions/code';

const initState = {
    templateType: [],
    templateTypeState: CODE_TEMPLATE_LIST_UNSET,
    selectedTemplateState: CODE_TEMPLATE_SELECTED_UNSET,
    selectedTemplateType: 'unknow',
    selectedTemplateContent: 'unknow',
    submitToggle: false,

    codeMetadataState: CODE_METADATA_UNSET,
    codeMetadata: null,

    codeInfoState: CODE_SUBMIT_UNSET,
    codeInfo: null,

    codeBuildState: CODE_BUILD_WAITING,

    codeBuildingProcess: 0,
    codeBuildingLastInfo: ''
};

export default function codeReduce(state = initState, action) {
    switch (action.type) {

        case CODE_TEMPLATE_LIST_REQUEST_POST:
            return state;

        case CODE_TEMPLATE_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            templateTypeState: CODE_TEMPLATE_LIST_SET,
            templateType: action.templateList
        });

        case CODE_TEMPLATE_REQUEST_POST:
            return state;

        case CODE_TEMPLATE_RECEIVE_POST:
            return Object.assign({}, state, {
            selectedTemplateState: CODE_TEMPLATE_SELECTED_SET,
            selectedTemplateType: action.templateType,
            selectedTemplateContent: action.templateContent
        });

        case CODE_SUBMIT_TOGGLE:
            return Object.assign({}, state, {
            submitToggle: !state.submitToggle
        });

        case CODE_RESET_METADATA:
            return Object.assign({}, state, {
            codeMetadataState: CODE_METADATA_UNSET    
        });

        case CODE_SUBMIT_METADATA:
            return Object.assign({}, state, {
            codeMetadataState: CODE_METADATA_SET,
            codeMetadata: action.metadata
        });

        case CODE_SUBMIT_CODE_INFO:
            return Object.assign({}, state, {
            codeInfoState: CODE_SUBMIT_SET,
            codeInfo: action.codeInfo
        });

        case CODE_RESET_CODE_INFO:
            return Object.assign({}, state, {
            codeInfoState: CODE_SUBMIT_UNSET
        });

        case CODE_BUILDING_RUNNING:
            return Object.assign({}, state, {
            codeBuildState: CODE_BUILD_RUNNING,
            codeBuildingProcess: 0,
            codeBuildingLastInfo: ''
        });

        case CODE_BUILDING_FINISHED:
            return Object.assign({}, state, {
            codeBuildState: CODE_BUILD_WAITING
        });

        case CODE_BUILDING_PROCESS:
            return Object.assign({}, state, {
            codeBuildingProcess: action.buildingProcess,
            codeBuildingLastInfo: action.buildingInfo
        });

        default:
            return state;
    };
};

