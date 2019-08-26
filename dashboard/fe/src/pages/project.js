import React from 'react';
import { connect } from 'react-redux';
import { PageHeader, Row, Col, Button, Drawer, Divider } from 'antd';
import RepoList from '../components/func_repo_list';
import CodeEditor from '../components/code_editor';
import CodeMetadata from '../components/code_metadata';
import CodeSelector from '../components/code_type_selector';
import CodeSubmitButton from '../components/code_submit_button';

class Page extends React.PureComponent {

    state = { drawerVisible: false }

    onClose = () => { this.setState({ drawerVisible: false }); }

    render() {
        return (
            <div>
                <PageHeader
                    title="项目"
                    extra={[<Button key="new" type="primary" onClick={() => this.setState({ drawerVisible: true })}>新建</Button>]} />

                <RepoList />

                <Drawer
                    title={(<div>新建项目 <small style={{marginLeft: 15, color: 'gray', marginRight: 10 }}>代码类别: </small><CodeSelector /></div>)}
                    visible={this.state.drawerVisible}
                    width={720}
                    onClose={this.onClose}>
                    <CodeMetadata />
                    <Divider orientation="left"><small>代码编辑</small></Divider>
                    <CodeEditor />
                    <div style={{
                        position: 'absolute',
                        left: 0,
                        bottom: 0,
                        width: '100%',
                        borderTop: '1px solid #e9e9e9',
                        textAlign: 'right',
                        padding: '10px 16px'
                    }}>
                        <Row gutter={24}>
                            <Col offset={18} span={3}>
                                <Button onClick={this.onClose}>取消</Button>
                            </Col>
                            <Col span={3}>
                                <CodeSubmitButton />
                            </Col>
                        </Row>
                    </div>
                </Drawer>
            </div>
        );
    }
}

export default connect()(Page);
