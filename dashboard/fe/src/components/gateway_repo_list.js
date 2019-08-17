import React from 'react';
import { Table } from 'antd';
import { connect } from 'react-redux';
import {
    fetchGatewayRepoList,
    GATEWAY_REPO_LIST_UNSET,
} from '../actions/repo';

class GatewayRepoList extends React.PureComponent {

    constructor(props) {
        super(props);

        if (this.props.repo.state === GATEWAY_REPO_LIST_UNSET) {
            this.props.dispatch(fetchGatewayRepoList());
        }
    }

    render() {
        const COLUMNS = [
            {
                title: '函数名称',
                dataIndex: 'repoName',
                key: 'repoName'
            },
            {
                title: '版本',
                key: 'repoVersion',
                dataIndex: 'repoVersion'
            },
            {
                title: '操作',
                key: 'operation',
                render: n => (
                    <div>
                    </div>
                )
            }
        ];

        let dataSource = [];
        if (this.props.repo.repo.map(n => dataSource.push({
            key: n.name,
            repoName: n.name,
            repoVersion: n.version
        })))
        
        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ repo }) => ({
    repo: repo.gatewayRepo
}))(GatewayRepoList);


